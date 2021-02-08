use proconio::input;
use std::collections::HashMap;

fn gcd(x: usize, y: usize) -> usize {
    if y == 0 {
        x
    } else {
        gcd(y, x % y)
    }
}

fn main() {
    input! {
        n: usize,
        a: [usize; n],
    }

    let mut factors: HashMap<usize, usize> = HashMap::new();
    let lo = *a.iter().min().unwrap();

    for i in 0..n {
        for j in 1..lo {
            if j * j > a[i] {
                break;
            }

            if a[i] % j == 0 {
                let original = *factors.entry(j).or_insert(a[i]);
                factors.insert(j, gcd(original, a[i]));
                if a[i] / j < lo {
                    let original = *factors.entry(a[i] / j).or_insert(a[i]);
                    factors.insert(a[i] / j, gcd(original, a[i]));
                }
            }
        }
    }

    let mut ans = 1;
    for (original, terminal) in factors {
        if original == terminal {
            ans += 1;
        }
    }

    println!("{}", ans);
}
