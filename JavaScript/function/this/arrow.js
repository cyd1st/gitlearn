day = 123
var a = {
    day: 456,
    getDay: function ()  {
        return () => this.day
    }
}
console.log(a.getDay()())
