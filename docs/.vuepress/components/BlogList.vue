<template>
  <div>
    <p v-if="loading">{{loadingText}}</p>
    <div v-if="!loading" class="keywords banner">
      <a
        class="keyword"
        v-for="keywordItem in keywordList"
        v-bind:href="getTagURL(keywordItem.key)"
      >{{`${keywordItem.key}: ${keywordItem.count}`}}</a>
    </div>
    <div class="article" v-for="page in files">
      <a v-bind:href="page.path">{{`${formatDate(page.frontmatter.published)} ${page.title}`}}</a>
      <div class="keywords">
        <a
          class="keyword"
          v-for="key in page.frontmatter.keywords"
          v-bind:href="getTagURL(key)"
        >{{key}}</a>
      </div>
    </div>
  </div>
</template>
<script>
export default {
  data() {
    return {loading: true, keywordMap: new Map(), keywordList: []};
  },
  computed: {
    files() {
      const blogs = this.$site.pages.filter((p) => {
        const baseCheck = p.path.indexOf('/blog/') >= 0 && p.path.length > 6;
        if (p.frontmatter && p.frontmatter.keywords)
          p.frontmatter.keywords.forEach((keyword) => {
            if (!this.keywordMap.has(keyword)) {
              this.keywordMap[keyword] = this.keywordList.length;
              this.keywordList.push({key: keyword, count: 0});
            }
            this.keywordList[this.keywordMap[keyword]].count++;
          });
        const advancedCheck = this.$route.query.tag
          ? p.frontmatter &&
            p.frontmatter.keywords &&
            p.frontmatter.keywords.findIndex(
              (it) => it.toLowerCase() === this.$route.query.tag.toLowerCase()
            ) !== -1
          : true;
        return baseCheck && advancedCheck;
      });
      this.loading = false;
      return blogs;
    },
    loadingText() {
      return this.$lang === 'zh-CN'
        ? '博客列表加载中……'
        : 'Loading Blog List...';
    },
  },
  methods: {
    formatDate(date) {
      return new Date(date).toLocaleString(this.$lang, {
        year: 'numeric',
        month: 'numeric',
        day: 'numeric',
      });
    },
    getTagURL(tag) {
      return `/blog/?tag=${tag}`;
    },
  },
};
</script>
<style lang="stylus" scoped>
.article {
  margin-bottom: 20px;
  border-left: solid 5px $accentColor;
  padding: 20px;
}

.banner {
  margin-bottom: 20px;
}

.keywords {
  margin-top: 20px;
}

.keyword {
  padding: 5px;
  border-radius: 7px;
  font-size: small;
  background: $accentColor;
  margin-right: 5px;
  color: white;
  font-weight: 500;
}
</style>
