package top.zsj.webserver.domain.response;


import lombok.AllArgsConstructor;
import lombok.Getter;

@Getter
@AllArgsConstructor
public enum ResultCode {

    SUCCESS(true,0,"成功"),
    UNKNOWN_REASON(false,-1,"未知错误"),
    BAD_SQL_SYNTAX(false,-2,"SQL语法错误"),
    JSON_PARSE_ERROR(false,-3,"Json解析错误"),
    PARAM_ERROR(false,-4,"参数错误"),
    FILE_UPLOAD_ERROR(false,-5,"文件上传错误"),
    EXCEPTION(false,-9999,"异常");


    private Boolean status;
    private Integer code;
    private String message;


}
