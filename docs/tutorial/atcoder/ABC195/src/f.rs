use proconio::input;

const PRIMES: [usize; 20] = [2, 3, 5, 7, 11, 13, 17, 19, 23, 29,
    31, 37, 41, 43, 47, 53, 59, 61, 67, 71];

fn main() {
    input! {
        a: usize,
        b: usize,
    }

    let mut dp = vec![0; 1 << 20];
    dp[0] = 1;
    for i in a..=b {
        let mut now = 0;
        for j in 0..20 {
            if i % PRIMES[j] == 0 {
                now = now | (1 << j);
            }
        }
        for last in (0..(1 << 20)).rev() {
            if (last & now) == 0 {
                dp[last ^ now] += dp[last];
            }
        }
    }

    let mut ans = 0;
    for i in 0..(1 << 20) {
        ans += dp[i];
    }

    println!("{}", ans);
}
