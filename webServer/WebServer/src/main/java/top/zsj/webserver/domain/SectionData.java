package top.zsj.webserver.domain;

import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;

import java.util.List;

@AllArgsConstructor
@NoArgsConstructor
@Data
public class SectionData {
    private Section section;
    private List<? extends BaseData> items;
}
