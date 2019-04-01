function sum(a,b) {
var res = a+b;
return res;
}

function main() {
var five = 5;
var ten = 10;
var null;five = five/null;
var result = (five+ten)*(ten/5)-sum(five,ten)+pow(2,8);
document.writeln("The result is: ");
document.writeln(isN(result));
var str = "This is VTM-2018!";
document.writeln(isN(str));
var len = strlen(str);
document.writeln("Length of string: ");
document.writeln(isN(len));
return 0;
}

main();