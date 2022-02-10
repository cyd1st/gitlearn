'use strict';
//注释
/*注释*/
//alert('你好！'); //注释
console.log(`你
好`)  // 多行字符串

function getAgeFromBirth(num) {
    var year = new Date().getFullYear();
    return year - this.birth - num;
}
var person = {
    name: 'null',
    birth: 1900,
    age: function () {
        return getAgeFromBirth(num);
    }
};

console.log(getAgeFromBirth.apply(person, [100]))

var count_parseInt = 0;
var oldParseInt = parseInt;
window.parseInt = function() {
    count_parseInt ++;
    //return oldParseInt.apply(null, arguments);
    return oldParseInt(arguments[0]);
}
console.log(parseInt('10'));
parseInt('20');
parseInt('30');
console.log('count = ' + count_parseInt); // 3

// High-order function
function addTest(x, y, f) {
    return f(x) + f(y);
}
console.log(addTest(-100, 24, Math.abs));

// map
function pow(x) {
    return x * x;
}
var arr = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9];
console.log(arr.map(pow))  // [0, 1, 4, 9, 16, 25, 36, 49, 64, 81]

// redece
function addtwo(x, y) {
    return x + y;
}
function multiplytwo(x, y) {
    return x * y;
}
var arr2 = [1, 2, 3, 4, 5, 6, 7, 8, 9];
console.log(arr2.reduce(addtwo));
console.log(arr2.reduce(multiplytwo));

// map + reduce
function string2int(s) {
    var arr = s.split("");
    var num = arr.map(x=>x-0).reduce((x,y)=>(x*10+y));
    return num;
}
console.log(string2int("123456789"))

//请把用户输入的不规范的英文名字，变为首字母大写，其他小写的规范名字。
//输入：['adam', 'LISA', 'barT']，输出：['Adam', 'Lisa', 'Bart']。
var arr = ['adam', 'LISA', 'barT']; 
function normalize(arr) {
    function f1(s) {
        var arr = s.split("");
        var arr1 = arr[0].toUpperCase();
        var arr2 = arr.slice(1).join("").toLowerCase();
        return arr1+arr2;
    }
    var arr2 = arr.map(f1);
    return arr2;
}
console.log(normalize(arr))

//filter
var arr = ['A', '', 'B', null, undefined, 'C', '  '];
console.log("before filter arr: %O", arr);
var arr = arr.filter(function(s) {
    return s && s.trim();
})  // filter empty elements
console.log("filter arr: %O", arr);

var arr = [1, 2, 3, 4, 5, 6];
var arr = arr.filter((s) => {return s % 2 !== 0}); // filter odd 
console.log(arr); //  [1, 3, 5]