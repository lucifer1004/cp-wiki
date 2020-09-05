const fs = require('fs');
const path = require('path');

module.exports = {
  getSubfolders(parent) {
    const dir = fs.readdirSync(path.join(process.cwd(), 'docs', parent), {
      withFileTypes: true,
    });
    const ans = [];
    for (const dirent of dir) {
      if (dirent.isDirectory()) ans.push(dirent.name + '/');
    }
    return ans;
  },
  range(l, r, prefix, reversed = false) {
    const v = [];
    for (let i = l; i <= r; ++i) v.push(reversed ? r + l - i : i);
    return v.map(it => `${prefix}${it}/`);
  },
};
