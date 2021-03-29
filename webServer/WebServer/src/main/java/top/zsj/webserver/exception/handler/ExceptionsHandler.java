package top.zsj.webserver.exception.handler;


import org.apache.log4j.Logger;
import org.springframework.beans.ConversionNotSupportedException;
import org.springframework.beans.TypeMismatchException;
import org.springframework.beans.factory.NoSuchBeanDefinitionException;
import org.springframework.http.converter.HttpMessageNotReadableException;
import org.springframework.http.converter.HttpMessageNotWritableException;
import org.springframework.jdbc.BadSqlGrammarException;
import org.springframework.web.bind.annotation.ExceptionHandler;
import org.springframework.web.bind.annotation.RestControllerAdvice;
import top.zsj.webserver.domain.response.ResponseResult;
import top.zsj.webserver.domain.response.ResultCode;

import java.io.FileNotFoundException;
import java.io.IOException;
import java.sql.SQLException;

@RestControllerAdvice
public class ExceptionsHandler {

    private static Logger log = Logger.getLogger(ExceptionsHandler.class);

    /** 运行时异常 */
    @ExceptionHandler(RuntimeException.class)
    public ResponseResult runtimeExceptionHandler(RuntimeException ex) {
        String errorInfo = "运行时异常: " + ex.getMessage();
        log.error(errorInfo);
        return ResponseResult.exception(errorInfo);
    }

    /** 空指针异常 */
    @ExceptionHandler(NullPointerException.class)
    public ResponseResult nullPointerExceptionHandler(NullPointerException ex) {
        ex.printStackTrace();
        String errorInfo = "空指针异常: " + ex.getMessage();
        log.error(errorInfo);
        return ResponseResult.exception(errorInfo);
    }

    /** 类型转换异常 */
    @ExceptionHandler(ClassCastException.class)
    public ResponseResult classCastExceptionHandler(ClassCastException ex) {
        String errorInfo = "类型转换异常: " + ex.getMessage();
//        log.error(errorInfo);
        ex.printStackTrace();
        return ResponseResult.exception(errorInfo);
    }
    /** 文件未找到异常 */
    @ExceptionHandler(FileNotFoundException.class)
    public ResponseResult FileNotFoundException(FileNotFoundException ex) {
        String errorInfo = "文件未找到异常: " + ex.getMessage();
        log.error(errorInfo);
        return ResponseResult.exception(errorInfo);
    }
    /** 数字格式异常 */
    @ExceptionHandler(NumberFormatException.class)
    public ResponseResult NumberFormatException(NumberFormatException ex) {
        String errorInfo = "数字格式异常: " + ex.getMessage();
        log.error(errorInfo);
        return ResponseResult.exception(errorInfo);
    }
    /** 安全异常 */
    @ExceptionHandler(SecurityException.class)
    public ResponseResult SecurityException(SecurityException ex) {
        String errorInfo = "安全异常: " + ex.getMessage();
        log.error(errorInfo);
        return ResponseResult.exception(errorInfo);
    }
    /** sql异常 */
    @ExceptionHandler(SQLException.class)
    public ResponseResult SQLException(SQLException ex) {
        String errorInfo = "sql异常: " + ex.getMessage();
        log.error(errorInfo);
        return ResponseResult.exception(errorInfo);
    }
    /** 类型不存在异常 */
    @ExceptionHandler(TypeNotPresentException.class)
    public ResponseResult TypeNotPresentException(TypeNotPresentException ex) {
        String errorInfo = "类型不存在异常: " + ex.getMessage();
        log.error(errorInfo);
        return ResponseResult.exception(errorInfo);
    }

    /** IO异常 */
    @ExceptionHandler(IOException.class)
    public ResponseResult iOExceptionHandler(IOException ex) {
        String errorInfo = "IO异常: " + ex.getMessage();
        log.error(errorInfo);
        return ResponseResult.exception(errorInfo);
    }

    /** 未知方法异常 */
    @ExceptionHandler(NoSuchMethodException.class)
    public ResponseResult noSuchMethodExceptionHandler(NoSuchMethodException ex) {
        String errorInfo = "未知方法异常: " + ex.getMessage();
        log.error(errorInfo);
        return ResponseResult.exception(errorInfo);
    }

    /** 数组越界异常 */
    @ExceptionHandler(IndexOutOfBoundsException.class)
    public ResponseResult indexOutOfBoundsExceptionHandler(IndexOutOfBoundsException ex) {
        String errorInfo = "数组越界异常: " + ex.getMessage();
        log.error(errorInfo);
        return ResponseResult.exception(errorInfo);
    }
    /** sql语法错误异常 */
    @ExceptionHandler(BadSqlGrammarException.class)
    public ResponseResult BadSqlGrammarException(BadSqlGrammarException ex) {
        String errorInfo = "sql语法错误异常: " + ex.getMessage();
        log.error(errorInfo);
        return ResponseResult.exception(errorInfo);
    }

    /** 无法注入bean异常 */
    @ExceptionHandler(NoSuchBeanDefinitionException.class)
    public ResponseResult NoSuchBeanDefinitionException(NoSuchBeanDefinitionException ex) {
        String errorInfo = "无法注入bean异常: " + ex.getMessage();
        log.error(errorInfo);
        return ResponseResult.exception(errorInfo);
    }

    /** Http消息不可读异常 */
    @ExceptionHandler({HttpMessageNotReadableException.class})
    public ResponseResult requestNotReadable(HttpMessageNotReadableException ex) {
        String errorInfo = "Http消息不可读异常: " + ex.getMessage();
        log.error(errorInfo);
        return ResponseResult.exception(errorInfo);
    }

    /** 400错误 */
    @ExceptionHandler({TypeMismatchException.class})
    public ResponseResult requestTypeMismatch(TypeMismatchException ex) {
        String errorInfo = "400错误: " + ex.getMessage();
        log.error(errorInfo);
        return ResponseResult.exception(errorInfo);
    }

    /** 500错误 */
    @ExceptionHandler({ConversionNotSupportedException.class, HttpMessageNotWritableException.class})
    public ResponseResult server500(RuntimeException ex) {
        String errorInfo = "500错误: " + ex.getMessage();
        log.error(errorInfo);
        return ResponseResult.exception(errorInfo);
    }

    /** 栈溢出 */
    @ExceptionHandler({StackOverflowError.class})
    public ResponseResult requestStackOverflow(StackOverflowError ex) {
        String errorInfo = "栈溢出: " + ex.getMessage();
        log.error(errorInfo);
        return ResponseResult.exception(errorInfo);
    }

    /** 除数不能为0 */
    @ExceptionHandler({ArithmeticException.class})
    public ResponseResult arithmeticException(ArithmeticException ex) {
        String errorInfo = "除数不能为0: " + ex.getMessage();
        log.error(errorInfo);
        return ResponseResult.exception(errorInfo);
    }

    /** 其他错误 */
    @ExceptionHandler({Exception.class})
    public ResponseResult exception(Exception ex) {
        String errorInfo = "其他错误: " + ex.getMessage();
        log.error(errorInfo);
        return ResponseResult.exception(errorInfo);
    }
}
