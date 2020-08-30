export default ({ Vue, options, router, siteData, isServer }) => {
  import('vue-google-adsense').then(Ads => {
    Vue.use(require('vue-script2'));
    Vue.use(Ads.default.Adsense);
    Vue.use(Ads.default.InArticleAdsense);
    Vue.use(Ads.default.InFeedAdsense);
  });
};
