use proconio::input;
use proconio::marker::Chars;

fn main() {
    input! {
        h: usize,
        w: usize,
        s: [Chars; h],
    }

    let mut extended = vec![vec!['.'; w * 2 + 1]; h * 2 + 1];
    for i in 1..h - 1 {
        for j in 1..w - 1 {
            if s[i][j] == '#' {
                for x in 2 * i..=2 * i + 2 {
                    for y in 2 * j..=2 * j + 2 {
                        extended[x][y] = '#';
                    }
                }
            }
        }
    }

    let mut outer = vec![vec![false; w * 2 + 1]; h * 2 + 1];
    for i in 1..h * 2 {
        for j in 1..=w * 2 {
            if extended[i][j] == '#' {
                for x in i - 1..=i + 1 {
                    for y in j - 1..=j + 1 {
                        if extended[x][y] == '.' {
                            outer[i][j] = true;
                        }
                    }
                }
            }
        }
    }

    let mut ans = 0;
    for i in 1..=h * 2 {
        for j in 1..=w * 2 {
            if outer[i][j] {
                if (outer[i - 1][j] && outer[i][j - 1]) || (outer[i][j - 1] && outer[i + 1][j]) || (outer[i + 1][j] && outer[i][j + 1]) || (outer[i][j + 1] && outer[i - 1][j]) {
                    ans += 1;
                }
            }
        }
    }

    println!("{}", ans);
}
