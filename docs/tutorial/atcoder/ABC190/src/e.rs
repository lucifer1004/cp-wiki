use proconio::input;
use proconio::marker::Usize1;
use std::collections::VecDeque;

const INF: usize = 1_000_000_000;

fn main() {
    input! {
        n: usize,
        m: usize,
        pairs: [(Usize1, Usize1); m],
        k: usize,
        c: [Usize1; k],
    }

    let mut adj: Vec<Vec<usize>> = vec![vec![]; n];
    for (u, v) in pairs.clone() {
        adj[u].push(v);
        adj[v].push(u);
    }

    let mut mapping = vec![k; n];
    for (i, u) in c.clone().into_iter().enumerate() {
        mapping[u] = i;
    }

    let mut dist: Vec<Vec<usize>> = vec![vec![INF; k]; k];
    for i in 0..k {
        let mut dq: VecDeque<(usize, usize)> = VecDeque::new();
        dq.push_back((c[i], 0));
        let mut vis = vec![false; n];
        vis[c[i]] = true;
        while !dq.is_empty() {
            let (u, steps) = dq.pop_front().unwrap();
            if mapping[u] != k {
                dist[i][mapping[u]] = steps;
            }
            for v in adj[u].clone() {
                if !vis[v] {
                    vis[v] = true;
                    dq.push_back((v, steps + 1));
                }
            }
        }
    }


    let mut ans = INF;

    let mut dp = vec![vec![INF; k]; 1 << k];
    for i in 0..k {
        dp[1 << i][i] = 1;
    }

    for state in 0..(1 << k) {
        for last in 0..k {
            if dp[state][last] < INF {
                for next in 0..k {
                    if state & (1 << next) == 0 {
                        dp[state ^ (1 << next)][next] = dp[state ^ (1 << next)][next].min(dp[state][last] + dist[last][next]);
                    }
                }
            }
        }
    }

    for i in 0..k {
        ans = ans.min(dp[(1 << k) - 1][i]);
    }

    if ans == INF {
        println!("-1");
    } else {
        println!("{}", ans);
    }
}
