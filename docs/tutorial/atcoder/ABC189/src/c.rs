use proconio::input;
use std::collections::VecDeque;

fn main() {
    input! {
        n: usize,
        mut a: [usize; n],
    }

    a.push(0);
    let mut ans = 0;
    let mut dq: VecDeque<(usize, usize)> = VecDeque::new();
    for i in 0..=n {
        let mut nl = i;
        while !dq.is_empty() && dq.back().unwrap().0 > a[i] {
            let (h, l) = *dq.back().unwrap();
            ans = ans.max(h * (i - l));
            dq.pop_back();
            nl = l;
        }
        if dq.is_empty() || dq.back().unwrap().0 < a[i] {
            dq.push_back((a[i], nl));
        }
    }
    println!("{}", ans);
}
