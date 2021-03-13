use proconio::input;

fn main() {
    input! {
        n: usize,
        m: usize,
        q: usize,
        bags: [(usize, usize); n],
        boxes: [usize; m],
        queries: [(usize, usize); q],
    }

    for (l, r) in queries {
        let mut available_boxes = vec![];
        for i in 0..l - 1 {
            available_boxes.push(boxes[i]);
        }
        for i in r..m {
            available_boxes.push(boxes[i]);
        }
        available_boxes.sort();
        let mut used = vec![false; n];
        let mut ans = 0;
        for b in available_boxes {
            let mut hi = 0;
            let mut hi_idx = n;
            for i in 0..n {
                if !used[i] && bags[i].0 <= b && bags[i].1 > hi {
                    hi = bags[i].1;
                    hi_idx = i;
                }
            }
            if hi_idx != n {
                used[hi_idx] = true;
                ans += hi;
            }
        }
        println!("{}", ans);
    }
}
