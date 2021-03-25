package top.zsj.webserver.domain.response;

import lombok.Data;

import java.util.HashMap;
import java.util.Map;

@Data
public class ResponseResult {
    private Boolean status;
    private Integer code;
    private String message;
    private Map<String,Object> data = new HashMap<>();

    public static ResponseResult exception(String message){
        ResponseResult r = new ResponseResult(ResultCode.EXCEPTION);
        r.setMessage(message);
        return r;
    }

    public static ResponseResult success(String message){
        ResponseResult r = new ResponseResult(ResultCode.SUCCESS);
        r.setMessage(message);
        return r;
    }

    private ResponseResult(){

    }

    public ResponseResult(Boolean status,Integer code,String message){
        this.status = status;
        this.code = code;
        this.message = message;
    }

    public ResponseResult(ResultCode result){
        setResultCode(result);
    }

    public ResponseResult(ResultCode result,String key,Object value){
        setResultCode(result);
        addData(key,value);
    }

    public ResponseResult(ResultCode result,Map<String,Object>data){
        setResultCode(result);
        this.data = data;
    }

    public void setResultCode(ResultCode result){
        this.status = result.getStatus();
        this.code = result.getCode();
        this.message = result.getMessage();
    }

    public void addData(String  key,Object value){
        data.put(key,value);
    }
}
