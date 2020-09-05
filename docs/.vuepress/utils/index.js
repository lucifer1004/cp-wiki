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
};
