/**
 * Creating objects with Classes
 * Versus objects with prototypes
 * Since JavaScript is not a Class-based language
 * what is happening behind the class syntax?
 */

let PersonC = class {
    constructor(nm, id) {
      this.name = nm;
      this.id = id;
    }
    getDetails() {
      return `${this.name} :: ${this.id}`;
    }
  };
  let bob = new PersonC("Bob", 123);
  console.log(bob.getDetails(), bob.name);
  
  let EmployeeC = class extends PersonC {
    // EmployeeC prototype links to PersonC prototype
    constructor(nm, id, salary) {
      super(nm, id);
      this.salary = salary;
    }
    employeeInfo() {
      //exist on the prototype of EmployeeC
      return `${this.name} :: ${this.id} :: ${this.salary}`;
    }
  };
  let noomi = new EmployeeC("Noomi", 456, 8500000);
  console.log(noomi.employeeInfo());
  
  ///////////////////////////////////////////////
  
  let PersonP = function(nm, id) {
    this.name = nm;
    this.id = id;
  };
  PersonP.prototype.getDetails = function() {
    return `${this.name} :: ${this.id}`;
  };
  let fred = new PersonP("Fred", 321);
  console.log(fred.getDetails(), fred.name);
  
  let EmployeeP = function(nm, id, salary) {
    PersonP.call(this, nm, id);
    this.salary = salary;
  };
  Object.setPrototypeOf(EmployeeP.prototype, PersonP.prototype); //extends NOTE: THIS LINE WAS CHANGED
  EmployeeP.prototype.employeeInfo = function() {
    return `${this.name} :: ${this.id} :: ${this.salary}`;
  };
  let mary = new EmployeeP("Mary", 654, 65000);
  console.log(mary.employeeInfo());