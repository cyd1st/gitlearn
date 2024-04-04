var a = ['A', 'B', 'C']
var s = new Set(a)
var m = new Map([[1, 'x'], [2, 'y'], [3, 'z']])

a.forEach((elemnt) => {
    console.log(elemnt)
})

s.forEach((element, _, set) => {
    console.log(element)
})

m.forEach((val, key, map) => {
    console.log('(' + key + ',' + val + ')')
}) 