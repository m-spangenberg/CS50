// collection of snarky greetings
const greeter_titles = [
    "commoner!",
    "street urchin!",
    "erfling!",
    "hyoo-mahn!",
    "zog!",
    "visitor!",
    "intruder!",
    "foreigner!",
    "carbon-based biped!",
    "fresh clone!",
    "alien!"
];

// wait for the DOM to load
window.addEventListener('load', function() {
    // select a random snarky greeting on every page load
    var random_greeting = greeter_titles[Math.floor(Math.random() * greeter_titles.length)];

    // display a random heading on each page load of index.html
    var greeting_element = document.getElementById('greeter');
    greeting_element.innerText = 'Welcome to Discworld, ' + random_greeting;
});

// function to hide introduction
function dismiss() {
    document.getElementById('introduction').style.display = "none";
};