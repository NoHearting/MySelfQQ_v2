package top.zsj.webserver.domain;

import lombok.*;

@AllArgsConstructor
@NoArgsConstructor
@Data
public class User {
    private Integer id;
    private String nickname;
    private String head;
    private String password;
    private String signature;   // 签名
    private Integer level;
    private Boolean vip;        // 是否vip
}
