use proconio::input;

const TEN: [i64; 4] = [1, 10, 100, 1000];

fn parse(s: String) -> i64 {
    let v = s.split(".").collect::<Vec<&str>>();
    if v.len() == 1 {
        v[0].parse::<i64>().unwrap() * 10000
    } else {
        let sub = v[1].parse::<i64>().unwrap();
        let len0 = v[1].len();
        if v[0].starts_with('-') {
            v[0].parse::<i64>().unwrap() * 10000 - sub * TEN[4 - len0]
        } else {
            v[0].parse::<i64>().unwrap() * 10000 + sub * TEN[4 - len0]
        }
    }
}

fn main() {
    input! {
        x: String,
        y: String,
        r: String,
    }

    let offset = 20_000_000_000_000;
    let offset_s = 2_000_000_000;

    let mut ans = 0i64;
    let x = parse(x);
    let y = parse(y);
    let r = parse(r);

    for i in (y - r + offset) / 10000 - offset_s..=(y + r - 1 + offset) / 10000 + 1 - offset_s {
        let h = y - i * 10000;

        let mut lo = -offset_s;
        let mut hi = x;

        while lo <= hi {
            let mid = (lo + hi) / 2;
            if (mid - x) * (mid - x) + h * h <= r * r {
                hi = mid - 1;
            } else {
                lo = mid + 1;
            }
        }

        let left = (lo - 1 + offset) / 10000 + 1 - offset_s;

        lo = x;
        hi = offset_s;

        while lo <= hi {
            let mid = (lo + hi) / 2;
            if (mid - x) * (mid - x) + h * h <= r * r {
                lo = mid + 1;
            } else {
                hi = mid - 1;
            }
        }
        let right = (hi + offset) / 10000 - offset_s;
        if right >= left {
            ans += right - left + 1;
        }
    }

    println!("{}", ans);
}
