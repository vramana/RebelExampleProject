/*
 * Copyright (c) 2015-present, Facebook, Inc.
 * All rights reserved.
 *
 * vim: set ft=rust:
 * vim: set ft=reason:
 */
open AtomReasonCommon;

type t;


/**
 * You can test source maps with:
 * -----------------------------
 *
 *  node -e "console.log(
 *    (new require('source-map').SourceMapConsumer(JSON.parse(require('fs').readFileSync('./app.map')))).originalPositionFor({line:5524, column:10})
 *  )"
 */

/**
   A typical Merlin payload might look something like:

  [
    {
      "start": { "line": 53, "col": 40 }, "end": { "line": 53, "col": 41 },
      "type": "type", "sub": [], "valid": true,
      "message": "Uninterpreted extension 'SyntaxError'."
    },
    {
      "start": { "line": 65, "col": 16 }, "end": { "line": 65, "col": 40 },
      "type": "type", "sub": [], "valid": true,
      "message": "Error: Unbound module MerlinService"
    },
    {
      "start": { "line": 66, "col": 35 }, "end": { "line": 66, "col": 48 },
      "type": "type", "sub": [], "valid": true,
      "message": "Error: Unbound value makeTellCommand"
    },
    {
      "start":{"line":5,"col":8},"end":{"line":5,"col":9},
      "type":"warning","sub":[], "valid":true,
      "message":"Warning 26: unused variable x.\n"
    }
  ]
 */

/**
 * This looks strange that we are converting to ML data but then quickly
 * converting back to JS types, but it will make more sense when everything
 * else above and below is ML, we have to start the conversion somewhere.
 */
let getMerlinDiagnostics editor::editor resolve reject => {
  let text = Atom.Buffer.getText (Atom.Editor.getBuffer editor);
  let path = AtomReasonCommon.path editor;
  SuperMerlin.getDiagnostics
    path::path
    text::text
    (
      fun successResult => resolve (
        MerlinServiceConvert.jsMerlinErrorsToNuclideDiagnostics path successResult
      )
    )
    reject
};
