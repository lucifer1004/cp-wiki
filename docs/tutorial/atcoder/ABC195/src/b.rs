use proconio::input;

fn main() {
    input! {
        a: usize,
        b: usize,
        mut w: usize,
    }

    w *= 1000;
    let hi = w / a;
    if w % a > hi * (b - a) {
        println!("UNSATISFIABLE");
    } else {
        let lo = if w % b == 0 {
            w / b
        } else {
            w / b + 1
        };
        println!("{} {}", lo, hi);
    }
}
