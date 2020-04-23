/*
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */

#pragma once

#include <arrow-glib/array.h>
#include <arrow-glib/schema.h>

G_BEGIN_DECLS

#define GARROW_TYPE_RECORD_BATCH (garrow_record_batch_get_type())
G_DECLARE_DERIVABLE_TYPE(GArrowRecordBatch,
                         garrow_record_batch,
                         GARROW,
                         RECORD_BATCH,
                         GObject)
struct _GArrowRecordBatchClass
{
  GObjectClass parent_class;
};

GArrowRecordBatch *garrow_record_batch_new(GArrowSchema *schema,
                                           guint32 n_rows,
                                           GList *columns,
                                           GError **error);

gboolean garrow_record_batch_equal(GArrowRecordBatch *record_batch,
                                   GArrowRecordBatch *other_record_batch);

GArrowSchema *garrow_record_batch_get_schema     (GArrowRecordBatch *record_batch);
GARROW_AVAILABLE_IN_1_0
GArrowArray  *garrow_record_batch_get_column_data(GArrowRecordBatch *record_batch,
                                                  gint i);
const gchar  *garrow_record_batch_get_column_name(GArrowRecordBatch *record_batch,
                                                  gint i);
guint         garrow_record_batch_get_n_columns  (GArrowRecordBatch *record_batch);
gint64        garrow_record_batch_get_n_rows     (GArrowRecordBatch *record_batch);
GArrowRecordBatch *garrow_record_batch_slice     (GArrowRecordBatch *record_batch,
                                                  gint64 offset,
                                                  gint64 length);

gchar        *garrow_record_batch_to_string      (GArrowRecordBatch *record_batch,
                                                  GError **error);

GArrowBuffer *GSerializeRecordBatch(GArrowRecordBatch *record_batch);

GArrowRecordBatch *garrow_record_batch_add_column(GArrowRecordBatch *record_batch,
                                                  guint i,
                                                  GArrowField *field,
                                                  GArrowArray *column,
                                                  GError **error);
GArrowRecordBatch *garrow_record_batch_remove_column(GArrowRecordBatch *record_batch,
                                                     guint i,
                                                     GError **error);

/////////////////////////
void arrow_builders_start(void);
GArrowSchema* getSchema(void);
GArrowRecordBatch* create_arrow_record_batch(gint64 count, GArrowArray *array_qName,GArrowArray *array_flag,GArrowArray *array_rID,GArrowArray *array_beginPos,GArrowArray *array_mapQ,
GArrowArray* array_cigar,GArrowArray *array_rNextId,GArrowArray *array_pNext,GArrowArray *array_tLen,GArrowArray *array_seq,GArrowArray *array_qual,GArrowArray *array_tags);
gboolean arrow_builders_append(gint32 builder_id, const gchar *qName, gint32 flag, gint32 rID, gint32 beginPos, gint32 mapQ, const gchar *cigar, gint32 rNextId, gint32 pNext, gint32 tLen, const gchar *seq, const gchar *qual, const gchar *tags);
GArrowRecordBatch* arrow_builders_finish(gint32 builder_id, gint64 count);
/////////////////////////


G_END_DECLS
