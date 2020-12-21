type align =
  [ `Start
  | `End
  | `Center ];

type distribute =
  [ `Around
  | `Between
  | `Evenly
  | `Start
  | `Center
  | `End ];

let gapStyles = (~unit, ~fit) => {
  let gap = Utils.toPx(unit * 4);

  switch (fit) {
  | true => [%css {|
      & > * {
        flex: 1 1 0%;
        margin-left: $gap;
      };

      &:first-child {
        margin-left: 0px;
      };
    |}]
  | false => [%css {|
      & > * {
        flex: 0 0 auto;
        margin-left: $gap;
      };

      &:first-child {
        margin-left: 0px;
      };
  |}];
  };
};

[@react.component]
let make =
    (
      ~gap=0,
      ~align: align=`Start,
      ~distribute=`Around,
      ~fullHeight=true,
      ~fullWidth=true,
      ~children,
    ) => {
  let className =
    Cn.make([
      [%css "display: flex; flex-direction: row;"],
      fullHeight ? [%css "height: 100%"] : [%css "height: auto"],
      fullWidth ? [%css "width: 100%"] : [%css "width: auto"],
      switch (align) {
      | `Start => [%css "align-items: flex-start"]
      | `Center => [%css "align-items: center"]
      | `End => [%css "align-items: flex-end"]
      },
      switch (distribute) {
      | `Around => [%css "justify-content: space-around"]
      | `Between => [%css "justify-content: space-between"]
      | `Evenly => [%css "justify-content: space-evenly"]
      | `Start => [%css "justify-content: flex-start"]
      | `Center => [%css "justify-content: center"]
      | `End => [%css "justify-content: flex-end"]
      },
      gapStyles(~unit=gap, ~fit=false),
    ]);

  <div className> children </div>;
};
