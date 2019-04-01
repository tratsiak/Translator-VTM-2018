function isN(a) {
 if(isNaN(a)) {
  return a;
} else {
 return Math.round(a);
 }
}