// let myHeading = document.querySelector('h1');
// myHeading.textContent = 'Hello world!';

let myImage = document.querySelector('img');

myImage.onclick = function() {
    let mySrc = myImage.getAttribute('src');
    if (mySrc === 'images/linux-log.png') {
        myImage.setAttribute('src', 'images/ubuntu.png');
    } else {
        myImage.setAttribute('src', 'images/linux-log.png');
    }
}

//
let myButton = document.querySelector('button');
let myHeading = docmument.querySelector('h1')

function setUserName() {
    let myName = prompt('你的名字。');
    localStorage.setItem('name', myName);
    myHeading.textContent = 'Hello ' + myName;
}
if (!localStorage.getItem('name')) {
    setUserName()
} else {
    myHeading.textContent = 'Hello ' + localStorage.getItem('name');
}
myButton.onclick = function() {
    setUserName()
}