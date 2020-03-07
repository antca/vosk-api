const greetNativeModule = require('./build/Release/greet.node');

function greetHello(name) {
    return greetNativeModule.greetHello(name);
}

module.exports = {
    greetHello,
};

