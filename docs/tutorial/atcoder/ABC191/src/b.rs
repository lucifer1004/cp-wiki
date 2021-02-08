use proconio::input;

fn main() {
    input! {
        n: usize,
        x: usize,
        a: [usize; n],
    }

    for num in a {
        if num != x {
            print!("{} ", num);
        }
    }
}
