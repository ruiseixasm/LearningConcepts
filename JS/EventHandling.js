function setColorGreen(event) {
    event.preventDefault();
    this.style.backgroundColor = "green";
}

function setColorRed(event) {
    event.preventDefault();
    this.style.backgroundColor = "red";
}

let capturing_elems = document.querySelectorAll("div.capturing, div.capturing *");
for (let elem of capturing_elems) {
    elem.addEventListener("click", setColorGreen, true);
}
let bubbling_elems = document.querySelectorAll("div.bubbling, div.bubbling *");
for (let elem of bubbling_elems) {
    elem.addEventListener("click", setColorRed, false);
}