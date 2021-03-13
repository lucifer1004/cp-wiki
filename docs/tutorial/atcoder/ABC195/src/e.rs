use proconio::input;
use proconio::marker::Chars;

fn main() {
    input! {
        n: usize,
        s: Chars,
        x: Chars,
    }

    let mut dp = vec![false; 7];
    dp[0] = true;
    for i in (0..n).rev() {
        let c = s[i].to_string().parse::<usize>().unwrap();
        let mut ndp = vec![false; 7];
        if x[i] == 'A' {
            // Aoki moves
            for last in 0..7 {
                let a = last * 10 % 7;
                let b = (last * 10 + c) % 7;
                if dp[a] && dp[b] {
                    ndp[last] = true;
                }
            }
        } else {
            // Takahashi moves
            for last in 0..7 {
                let a = last * 10 % 7;
                let b = (last * 10 + c) % 7;
                if dp[a] || dp[b] {
                    ndp[last] = true;
                }
            }
        }
        dp = ndp;
    }

    println!("{}", if dp[0] { "Takahashi" } else { "Aoki" });
}
