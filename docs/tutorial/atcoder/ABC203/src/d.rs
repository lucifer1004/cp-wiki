use proconio::input;

fn main() {
    input! {
        n: usize,
        k: usize,
        a: [[usize; n]; n],
    }

    let pos = (k * k - 1) / 2 + 1;

    let mut lo: i32 = 0;
    let mut hi: i32 = 1_000_000_000;
    let mut v = vec![vec![0; n]; n];
    let mut s = vec![vec![0; n + 1]; n + 1];

    while lo <= hi {
        let mid = (lo + hi) >> 1;
        for i in 0..n {
            for j in 0..n {
                if a[i][j] <= mid as usize {
                    v[i][j] = 1;
                } else {
                    v[i][j] = 0;
                }
            }
        }
        for i in 1..=n {
            for j in 1..=n {
                s[i][j] = s[i - 1][j] + s[i][j - 1] - s[i - 1][j - 1] + v[i - 1][j - 1];
            }
        }

        if s[n][n] < pos {
            lo = mid + 1;
            continue;
        }

        let mut found = false;
        for i in k..=n {
            for j in k..=n {
                if s[i][j] - s[i - k][j] - s[i][j - k] + s[i - k][j - k] >= pos {
                    found = true;
                    break;
                }
            }
            if found {
                break;
            }
        }

        if found {
            hi = mid - 1;
        } else {
            lo = mid + 1;
        }
    }

    println!("{}", lo);
}
