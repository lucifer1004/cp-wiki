<template>
  <div id="comment"></div>
</template>
<script>
export default {
  name: 'Utterances',
  methods: {
    initValine() {
      const utterances = document.createElement('script');
      utterances.type = 'text/javascript';
      utterances.async = true;
      utterances.setAttribute('issue-term', 'og:title');
      utterances.setAttribute('theme', 'github-light');
      utterances.setAttribute('repo', `lucifer1004/cp-wiki`);
      utterances.crossorigin = 'anonymous';
      utterances.src = 'https://utteranc.es/client.js';
      window.document.getElementById('comment').appendChild(utterances);
    },
  },
  mounted: function() {
    this.initValine();
  },
};
</script>
