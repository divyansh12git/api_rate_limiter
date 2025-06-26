import express from "express"
import {router} from "./requests"
const app=express();
const PORT:Number=8050


app.use(express.json());
app.get('/',(req,res)=>{
    res.send({"author":"Divyansh Gupta"})
})

app.use('/limiter',router);

app.listen(PORT || 3001,()=>{
    console.log("app started on PORT:",PORT);
})
