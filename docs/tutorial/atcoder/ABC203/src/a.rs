use proconio::input;

fn main() {
    input! {
        a: usize,
        b: usize,
        c: usize,
    }

    if a == b {
        println!("{}", c);
    } else if a == c {
        println!("{}", b);
    } else if b == c {
        println!("{}", a);
    } else {
        println!("0");
    }
}
