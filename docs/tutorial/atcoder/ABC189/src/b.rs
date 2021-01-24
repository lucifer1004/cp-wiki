use proconio::input;

fn main() {
    input! {
        n: usize,
        mut x: usize,
        liquor: [(usize, usize); n],
    }

    x *= 100;
    let mut tot = 0;
    for i in 0..n {
        tot += liquor[i].0 * liquor[i].1;
        if tot > x {
            println!("{}", i + 1);
            return;
        }
    }
    println!("-1");
}
