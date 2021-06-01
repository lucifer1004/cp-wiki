use std::collections::HashSet;

use proconio::input;

fn main() {
    input! {
        n: usize,
        m: usize,
        mut black: [(usize, usize); m],
    }

    black.sort();
    let mut pos: HashSet<usize> = HashSet::new();
    pos.insert(n);

    let mut l = 0;
    let mut r = 0;
    while l < m {
        while r + 1 < m && black[r + 1].0 == black[l].0 {
            r += 1;
        }
        let mut insert = vec![];
        let mut remove = vec![];
        for i in l..=r {
            let y = black[i].1;
            remove.push(y);
            if y > 0 && pos.contains(&(y - 1)) {
                insert.push(y);
            }
            if y + 1 <= 2 * n && pos.contains(&(y + 1)) {
                insert.push(y);
            }
        }
        for i in remove {
            pos.remove(&i);
        }
        for i in insert {
            pos.insert(i);
        }
        l = r + 1;
    }

    println!("{}", pos.len());
}
