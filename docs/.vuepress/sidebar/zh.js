module.exports = {
  "/basic/": ["enumerate/", "binary-search/", "ternary-search/"],
  "/algebra/": ["binary-exponentiation/", "fast-fourier-transform/"],
  "/data-structure/": [
    {
      title: "基础数据结构",
      collapsable: false,
      children: ["stack/", "queue/"],
    },
    {
      title: "进阶数据结构",
      collapsable: false,
      children: ["disjoint-union/", "segment-tree/"],
    },
  ],
  "/graph-theory/": [""],
  "/geometry/": ["basic/"],
  "/string/": ["prefix-function/", "trie/", "aho-corasick/"],
  "/combinatorics/": ["inclusion-exclusion/"],
  "/editorial/kick-start/": ["", {
    title: "2020",
    collapsable: false,
    children: ["2020E/", "2020D/"],
  }, {
    title: "2019",
    collapsable: false,
    children: ["2019G/", "2019F/", "2019C/"],
  }],
  "/": "auto",
};
