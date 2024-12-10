fn main() {
    let x = 5;
    let y = x;  // Copy by value
    println!("{} {}", x, y);
    let s1 = String::from("hello");
    let s2 = s1;  // Moves ownership of s1 and thus s1 is no longer valid!
    println!("{}", s2); // println!(s2) doesn't work
}
