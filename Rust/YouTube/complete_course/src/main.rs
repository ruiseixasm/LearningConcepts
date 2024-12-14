fn main() {
    example_reference();
    mutable_reference();
    violates_borrowing();
    working_borrowing();
    inactive_borrowing();
    println!("String value: {}", string_value());
    new_reference();
}

// Example Reference: https://youtu.be/BpPEoZW5IiY?si=imiLftI8HIvAWRCs&t=8869

fn example_reference() {
    let s1 = String::from("hello");
    let len = calculate_length(&s1);
    println!("The length of '{}' is {}.", s1, len);
}
fn calculate_length(s: &String) -> usize {
    s.len() // Implicit return, no need for "return keyword"
}

fn mutable_reference() {
    let mut s = String::from("hello");
    change(&mut s);
    println!("Mutable string is '{}'.", s);
}
fn change(some_string: &mut String) {
    some_string.push_str(", world");
}

fn violates_borrowing() {
    // This would violate the first rule of borrowing,
    // which says that we can only have ONE mutable reference <- BUT multiple immutable (just)
    // to the same data at a time!
    let mut s = String::from("hello");
    let r1 = &mut s;
    // let r2 = &mut s;

    // println!("{}, {}", r1, r2);
    println!("Violating borrowing is '{}'.", r1);
}

fn working_borrowing() {
    let mut s = String::from("hello");

    {
        let _r1 = &mut s;
    }   // _r1 goes out of scope here, so we can make a new reference with no problems.

    let r2 = &mut s;
    println!("Working borrowing is '{}'.", r2);
}

// fn active_borrowing() {
//     let mut s = String::from("hello");

//     let r1 = &s;
//     let r2 = &s;
//     // This would violate the first rule of borrowing,
//     // which says that we can either have any number
//     // of immutable references or one single mutable reference.
//     let r3 = &mut s;

//     println!("{}, {}, and {}", r1, r2, r3);
// }

fn inactive_borrowing() {
    let mut s = String::from("hello");

    let r1 = &s;
    let r2 = &s;
    println!("{} and {}", r1, r2);
    // Variables r1 and r2 will NOT be used after this point

    let r3 = &mut s;
    println!("Just {}", r3);    // No problem!
}

// fn dangling_reference() -> &String {
//     let s = String::from("hello");
//     // This will violate the second rule which states that
//     // references must ALWAYS be valid
//     &s
// }

fn string_value() -> String {
    let s = String::from("hello");
    s
}

fn new_reference() {
    let c: char = '中';

    let r1: &char = &c;
    let r2: &char = &c;
    let ref r3 = c;

    assert_eq!(*r1, *r2);
    assert_eq!(*r1, *r3);
    // Check the equality of the two string addresses
    assert_eq!(get_addr(r1), get_addr(r2));
    assert_eq!(get_addr(r1), get_addr(r3));

    println!("Success!")
}
// Get memory address string
fn get_addr(r: &char) -> String {
    format!("{:p}", r)  // returns the memory address as string (:)
}

