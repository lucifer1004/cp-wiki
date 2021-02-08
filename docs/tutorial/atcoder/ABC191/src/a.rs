use proconio::input;

fn main() {
    input! {
        v: usize,
        t: usize,
        s: usize,
        d: usize,
    }

    println!("{}", if d < v * t || d > v * s {"Yes"} else {"No"});
}
