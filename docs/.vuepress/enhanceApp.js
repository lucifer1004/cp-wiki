export default ({ Vue, options, router, siteData, isServer }) => {
  if (!isServer) {
    import('vue-google-adsense').then(Ads => {
      Vue.use(require('vue-script2'));
      Vue.use(Ads.Adsense);
      Vue.use(Ads.InArticleAdsense);
      Vue.use(Ads.InFeedAdsense);
    });
  }
};
