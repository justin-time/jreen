import qbs.base 1.0
import qbs.fileinfo as FileInfo
import "utils.js" as Utils

Probe {
    // Inputs
    property string executable: 'pkg-config'
    property string name
    property string minVersion
    property string exactVersion
    property string maxVersion

    // Output
    property var cflags
    property var libs

    configure: {
        if (!name)
            throw '"name" must be specified';
        var p = new Process();
        var args = [ name ];
        if (minVersion !== undefined)
            args.push(name + ' >= ' + minVersion);
        if (exactVersion !== undefined)
            args.push(name + ' = ' + exactVersion);
        if (maxVersion !== undefined)
            args.push(name + ' <= ' + maxVersion);
        if (p.exec(executable, args.concat([ '--cflags' ])) === 0) {
            cflags = p.readAll().trim();
            if (cflags === "")
                cflags = undefined; 
            else
                cflags = cflags.split(/\s/);
            if (p.exec(executable, args.concat([ '--libs' ])) === 0) {
                libs = p.readAll().trim();
                if (libs === "")
                    libs = undefined;
                else
                    libs = libs.split(/\s/); 
                found = true;
                print("PkgConfigProbe: found library " + name);
                return;
            }
        }
        found = false;
        cflags = undefined;
        libs = undefined;
    }
}
