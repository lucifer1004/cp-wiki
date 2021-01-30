use proconio::input;
use std::collections::HashSet;

fn main() {
    input! {
        n: i64,
    }

    let mut factors = HashSet::new();
    let x = n * 2;

    let mut i = 1i64;
    while i * i <= x {
        if x % i == 0 {
            factors.insert(i.clone());
            factors.insert((x / i).clone());
        }
        i += 1;
    }

    let mut ans = 0;
    for k in factors {
        let rem = x / k;
        if (rem + 1 - k) % 2 == 0 {
            ans += 1;
        }
    }

    println!("{}", ans);
}
