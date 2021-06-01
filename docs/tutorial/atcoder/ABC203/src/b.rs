use proconio::input;

fn main() {
    input! {
        n: usize,
        k: usize,
    }

    println!("{}", n * (n + 1) / 2 * k * 100 + k * (k + 1) / 2 * n);
}
