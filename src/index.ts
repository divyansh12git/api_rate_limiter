const addon = require('./api_rate_limiter.node');

// console.log(addon.helloWorld());  

// for(let i = 0; i < 10; i++) {
    setInterval(() => {
        for(let t=0;t<10;t++){
            let ans:boolean=addon.checkFixed("1234");
            console.log("user status: ",ans);
        }
    }, 5000);
// }