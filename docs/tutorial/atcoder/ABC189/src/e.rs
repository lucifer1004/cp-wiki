use proconio::input;
use proconio::marker::Usize1;
use std::cmp::Ordering;

fn main() {
    input! {
        n: usize,
        points: [(i64, i64); n],
        m: usize,
    }

    let mut ops: Vec<(usize, i64)> = vec![];
    for _i in 0..m {
        input! {
            t: usize,
        }
        if t <= 2 {
            ops.push((t, 0));
        } else {
            input! {
                p: i64,
            }
            ops.push((t, p));
        }
    }

    input! {
        q: usize,
        queries: [(usize, Usize1); q],
    }

    let mut ans = vec![(0i64, 0i64); q];
    let mut order: Vec<usize> = (0..q).collect();
    order.sort_by(|a, b| if queries[*a].0 <= queries[*b].0 {
        Ordering::Less
    } else {
        Ordering::Greater
    });

    let mut swap = false;
    let mut sx = 1i64;
    let mut sy = 1i64;
    let mut cx = 0i64;
    let mut cy = 0i64;
    let mut op = 0usize;
    for i in order {
        let (a, b) = queries[i];
        while op < a {
            let (t, p) = ops[op];
            match t {
                1 => {
                    swap = !swap;
                    std::mem::swap(&mut cx, &mut cy);
                    std::mem::swap(&mut sx, &mut sy);
                    sy = -sy;
                    cy = -cy;
                },
                2 => {
                    swap = !swap;
                    std::mem::swap(&mut cx, &mut cy);
                    std::mem::swap(&mut sx, &mut sy);
                    sx = -sx;
                    cx = -cx;
                },
                3 => {
                    sx = -sx;
                    cx = p * 2 - cx;
                },
                4 => {
                    sy = -sy;
                    cy = p * 2 - cy;
                },
                _ => {

                }
            }
            op += 1;
        }
        if swap {
            ans[i] = (points[b].1 * sx + cx, points[b].0 * sy + cy);
        } else {
            ans[i] = (points[b].0 * sx + cx, points[b].1 * sy + cy);
        }
    }

    for i in 0..q {
        println!("{} {}", ans[i].0, ans[i].1);
    }
}
