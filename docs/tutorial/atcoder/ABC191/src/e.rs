use proconio::input;
use proconio::marker::Usize1;
use std::collections::BinaryHeap;

const INF: i64 = 1_000_000_000_000;

fn main() {
    input! {
        n: usize,
        m: usize,
        edges: [(Usize1, Usize1, i64); m],
    }

    let mut adj: Vec<Vec<(usize, i64)>> = vec![vec![]; n];
    for (u, v, c) in edges {
        adj[u].push((v, c));
    }

    let mut ans = vec![-1; n];
    for i in 0..n {
        let mut dist = vec![INF; n];
        let mut pq: BinaryHeap<(i64, usize)> = BinaryHeap::new();
        pq.push((0, i));
        while !pq.is_empty() {
            let (d, u) = pq.pop().unwrap();
            let d = -d;
            if d > dist[u] {
                continue;
            }
            for (v, c) in adj[u].clone() {
                if d + c < dist[v] {
                    dist[v] = d + c;
                    pq.push((-dist[v], v));
                }
            }
        }
        if dist[i] != INF {
            ans[i] = dist[i];
        }
    }

    for i in ans {
        println!("{}", i);
    }
}
