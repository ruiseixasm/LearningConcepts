function beginDrag(elementToDrag, event) {

    let x = parseInt(elementToDrag.style.left);
    let y = parseInt(elementToDrag.style.top);
    
    let deltaX = event.clientX - x;
    let deltaY = event.clientY - y;

    document.addEventListener("mousemove", moveHandler, true);
    document.addEventListener("mouseup", upHandler, true);

    event.stopPropagation();
    event.preventDefault();

    function moveHandler(event) {
        elementToDrag.style.left = (event.clientX - deltaX) + "px";
        elementToDrag.style.top = (event.clientY - deltaY) + "px";

        event.stopPropagation();
    }

    function upHandler(event) {
        document.removeEventListener("mouseup", upHandler, true);
        document.removeEventListener("mousemove", moveHandler, true);

        event.stopPropagation();
    }
}