-- Keep a log of any SQL queries you execute as you solve the mystery.
-- Take a look at the crime scene report and look to see if there were similar incidents in the immediate area
SELECT description FROM crime_scene_reports WHERE street="Chamberlin Street";
-- Take a look at the transcripts on record for the 28th
SELECT transcript FROM interviews WHERE month=7 AND day=28;
-- Take a look at withdrawals on Fifer Street that day
SELECT * FROM atm_transactions WHERE month=7 AND day=28 AND transaction_type='withdraw' AND atm_location='Fifer Street';
-- Check when the earliest flight is out of town on the 29th
SELECT * FROM flights WHERE month=7 AND day=29;
-- Where did the 8:20 flight leave to?
SELECT * FROM airports WHERE id=4;
-- Check if there is any correlation between:
-- A car in the courthouse logs leaving within 10 minutes of the theft at 10:15am
-- passengers leaving for Heathrow Airport on the 29th
-- people who withdrew money on Fifer Street
-- and who made a sub 60 second call on the 28th
SELECT DISTINCT people.name, phone_calls.receiver
FROM people
INNER JOIN passengers ON passengers.passport_number=people.passport_number
INNER JOIN flights ON passengers.flight_id=flights.id
INNER JOIN courthouse_security_logs ON people.license_plate=courthouse_security_logs.license_plate
INNER JOIN phone_calls ON phone_calls.caller=people.phone_number
INNER JOIN bank_accounts ON bank_accounts.person_id=people.id
INNER JOIN atm_transactions ON bank_accounts.account_number=atm_transactions.account_number
WHERE flights.month=7 AND flights.day=29 AND destination_airport_id=4 AND courthouse_security_logs.month=7
AND courthouse_security_logs.day=28 AND atm_transactions.month=7 AND atm_transactions.day=28 AND atm_transactions.atm_location='Fifer Street'
AND phone_calls.month=7 AND phone_calls.day=28 AND phone_calls.duration < 60 AND courthouse_security_logs.hour=10 AND courthouse_security_logs.minute <25;
-- Let's see who Ernest was speaking to on the phone
SELECT DISTINCT people.name
FROM people
WHERE people.phone_number='(375) 555-8161';
-- Ernest, you sneaky fish! We have you and your nefarious chum Berthold in our net now!
