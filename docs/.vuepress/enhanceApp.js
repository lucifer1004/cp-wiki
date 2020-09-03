export default ({ Vue, options, router, siteData, isServer }) => {
  if (!isServer) {
    import('vue-google-adsense')
      .then(module => {
        const Ads = module.default;
        Vue.use(require('vue-script2'));
        Vue.use(Ads.Adsense);
        Vue.use(Ads.InArticleAdsense);
        Vue.use(Ads.InFeedAdsense);
      })
      .catch(e => {
        console.log(e);
      });
  }

  //// This might be used in the future
  // router.addRoutes([
  //   {
  //     path: '/tag/:tag',
  //     component: BlogListByTag,
  //   },
  // ]);
};
