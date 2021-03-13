use proconio::input;

fn main() {
    input! {
        n: usize,
    }

    let mut base: usize = 1_000;
    let mut ans: usize = 0;
    let mut cnt = 3;
    while base <= n {
        let num = (n - base + 1).min(base * 9);
        ans += num * (cnt / 3);
        cnt += 1;
        base *= 10;
    }
    println!("{}", ans);
}
