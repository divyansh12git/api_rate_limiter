const addon = require('./api_rate_limiter.node');
import express from "express"
const router = express.Router();


type Response={
    activity:boolean,
    answer:string
};

function getResponse(param:number):Response{
    const str=["need username as uery params","user allowed","user not allowed"]
    const resp:Response={
        activity:param==1?true:false,
        answer:str[param]
    }
    return resp;
};

router.get('/fixed',(req,res)=>{
    const username:any=req.query.name;
    // console.log(username);
    if(username && typeof(username)=="string"){
        let ans:boolean=addon.checkFixed(username);
        res.json(getResponse(ans?1:2)).status(200);
        return;
    } 
    res.json(getResponse(0)).status(500);
});

router.get('/sliding',(req,res)=>{
    const username:any=req.query.name;
    // console.log(username);
    if(username && typeof(username)=="string"){
        let ans:boolean=addon.checkSliding(username);
        res.json(getResponse(ans?1:2)).status(200);
        return;
    } 
    res.json(getResponse(0)).status(500);
});

router.get('/token',(req,res)=>{
    const username:any=req.query.name;
    // console.log(username);
    if(username && typeof(username)=="string"){
        let ans:boolean=addon.checkToken(username);
        res.json(getResponse(ans?1:2)).status(200);
        return;
    } 
    res.json(getResponse(0)).status(500);
});

router.get('/leaky',(req,res)=>{
    const username:any=req.query.name;
    // console.log(username);
    if(username && typeof(username)=="string"){
        let ans:boolean=addon.checkLeaky(username);
        res.json(getResponse(ans?1:2)).status(200);
        return;
    } 
    res.json(getResponse(0)).status(500);
});




export {router};