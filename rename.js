const fs = require('fs');
const path = require('path');

function isRegExp(str) {
  try {
    new RegExp(str);
    return true;
  } catch (e) {
    return false;
  }
}


function renameDir(dirPath, oldName, newName) {
  fs.readdir(dirPath, (err, files) => {
    if (err) {
      console.error(err);
      return;
    }
    files.forEach(file => {
      const filePath = path.join(dirPath, file);
      fs.stat(filePath, (err, stats) => {
        if (err) {
          console.error(err);
          return;
        }
        if (stats.isDirectory()) {

          if ( isRegExp(oldName) ? new RegExp(oldName).test(file) : file === oldName ) {
            const newFilePath = path.join(dirPath, newName);
            fs.rename(filePath, newFilePath, err => {
              if (err) {
                console.error(err);
              }
            });
          } else {
            renameDir(filePath, oldName, newName);
          }
        }
      });
    });
  });
}

renameDir('./', /^lesson\d{1,2}$/, 'arduino');


