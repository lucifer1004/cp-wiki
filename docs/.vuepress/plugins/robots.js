const fs = require('fs');
const path = require('path');
const robotstxt = require('generate-robotstxt');

module.exports = (options, ctx) => {
  // Get options
  const {
    allowAll = false, // Allow All: false by default
    disallowAll = false, // Disallow all: false by default
    host, // Base URL
    sitemap = '/sitemap.xml', // Default sitemap is sitemap.xml
    policies, // Default policies is null
    outputFile = 'robots.txt', // Default robots is robots.txt
  } = options;

  return {
    async generated(pagePaths) {
      console.log('Generating robots.txt ...');

      if (ctx.isProd === true) {
        const robotsTxt = path.resolve(ctx.outDir, outputFile);

        // Get all policies togeter; If none provided, it will allow all except path: /admin
        let policyArray = [];

        const disallowAllPolicy = {
          userAgent: '*',
          disallow: '/',
        };
        const allowAllPolicy = {
          userAgent: '*',
          disallow: '',
        };

        if (disallowAll) {
          policyArray.push(disallowAllPolicy);
        } else {
          if (allowAll) {
            policyArray.push(allowAllPolicy);
          } else {
            // allowAll and disallowAll not provided, then use policies
            if (typeof policies !== 'undefined' && policies.length > 0) {
              policies.forEach(policy => {
                policyArray.push(policy);
              });
            } else {
              policyArray.push(allowAllPolicy);
            }
          }
        }

        const sitemapUrl = host + sitemap;

        robotstxt({
          policy: policyArray,
          sitemap: sitemapUrl,
          host: host,
        })
          .then(content => {
            // All good, save the file
            fs.writeFileSync(robotsTxt, content);
            return content;
          })
          .catch(error => {
            // Something wrong
            throw error;
          });
      } else {
        console.log('You need robots.txt file only in the production server.');
      }
    },
  };
};
