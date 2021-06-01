use proconio::input;

const K: usize = 31;

fn main() {
    input! {
        n: usize,
        k: usize,
        mut a: [usize; n],
    }

    if k == n {
        println!("0 {}", n);
        std::process::exit(0);
    }

    a.sort();
    let mut l = vec![0; n];
    for i in 0..n {
        let mut lo = 0;
        let mut hi = i;
        while lo <= hi {
            let mid = (lo + hi) >> 1;
            if a[mid] > a[i] / 2 {
                if mid == 0 {
                    break;
                }
                hi = mid - 1;
            } else {
                lo = mid + 1;
            }
        }
        l[i] = lo;
    }

    let mut dp = vec![vec![k + 1; K]; n + 1];
    dp[0][0] = 0;
    for i in 0..n {
        for j in 0..K {
            if j + 1 < K {
                dp[i + 1][j + 1] = dp[i + 1][j + 1].min(dp[l[i]][j]);
            }
            dp[i + 1][j] = dp[i + 1][j].min(dp[i][j] + 1);
        }
    }

    for i in 1..K {
        if dp[n][i] <= k {
            println!("{} {}", i, dp[n][i]);
            std::process::exit(0);
        }
    }
}