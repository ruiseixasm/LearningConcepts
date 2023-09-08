let PersonP = function(nm, id) {
    this.name = nm;
    this.id = id;
};
PersonP.prototype.getDetails = function() {
    return `${this.name} :: ${this.id}`;
};

let fred = new PersonP("Fred", 321);
console.log(fred.getDetails());

let EmployeeP = function(nm, id, salary) {
    PersonP.call(this, nm, id); // Calls super constructer as this
    this.salary = salary;
};
Object.setPrototypeOf(EmployeeP, PersonP.prototype); // Extends PersonP
EmployeeP.prototype.EmployeeInfo = function() {
    return `${this.name} :: ${this.id} :: ${this.salary}`;
};

let mary = new EmployeeP("Mary", 654, 65000);
console.log(mary.EmployeeInfo());