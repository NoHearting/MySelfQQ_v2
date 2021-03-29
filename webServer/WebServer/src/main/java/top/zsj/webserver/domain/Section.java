package top.zsj.webserver.domain;

import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;

/**
 * 分组
 */
@Data
@AllArgsConstructor
@NoArgsConstructor
public class Section {
    public Section(String sectionName, Long belong, Integer size, Boolean type) {
        this.sectionName = sectionName;
        this.belong = belong;
        this.size = size;
        this.type = type;
    }

    private Long id;         // 主键id
    private String sectionName; // 分组名称
    private Long belong;     // 分组所有者（这是哪个用户的分组）
    private Integer size;       // 分组当前的人数
    private Boolean type;       // 分组类型（群分组 true or 用户分组 false）
}
